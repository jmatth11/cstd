const std = @import("std");

fn createModule(b: *std.Build, optimize: std.builtin.OptimizeMode, target: std.Build.ResolvedTarget) *std.Build.Module {
    const files: []const []const u8 = &.{
        "src/base_str.c",
        "src/crypt.c",
        "src/file_ops.c",
        "src/gap_buffer.c",
        "src/hash_map.c",
        "src/linked_list.c",
        "src/log.c",
        "src/unicode_str.c",
    };
    const flags: []const []const u8 = &.{
        "-Wall",
        "-O2",
        "-std=c11",
        "-lm",
        "-D__EMSCRIPTEN__=1",
    };
    const module = b.addModule("custom_std", .{
        .pic = true,
        .target = target,
        .optimize = optimize,
    });
    module.addCSourceFiles(.{
        .language = .c,
        .files = files,
        .flags = flags,
    });
    module.addIncludePath(b.path("."));
    module.addIncludePath(b.path("./deps/utf8-zig/headers/"));
    module.addIncludePath(.{ .cwd_relative = "/usr/include/x86_64-linux-gnu" });
    module.addIncludePath(.{ .cwd_relative = "/usr/include" });
    return module;
}

pub fn build(b: *std.Build) void {
    const optimize = b.standardOptimizeOption(.{});
    const webTarget = b.resolveTargetQuery(.{ .cpu_arch = .wasm32, .os_tag = .freestanding });
    const webLib = b.addLibrary(.{
        .name = "webcustom_std",
        .linkage = .static,
        .root_module = createModule(b, optimize, webTarget),
        .use_llvm = true,
    });
    b.installArtifact(webLib);
    const linkage = b.option(std.builtin.LinkMode, "linkage", "Link mode for custom_std library") orelse .static;
    const nativeTarget = b.standardTargetOptions(.{});
    const nativeLib = b.addLibrary(.{
        .name = "custom_std",
        .linkage = linkage,
        .root_module = createModule(b, optimize, nativeTarget),
    });
    b.installArtifact(nativeLib);
}
