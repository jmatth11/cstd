const std = @import("std");

pub fn build(b: *std.Build) void {
    //const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{
        .preferred_optimize_mode = .ReleaseFast,
    });
    const linkage = b.option(std.builtin.LinkMode, "linkage", "Link mode for scribe library") orelse .static;
    const webTarget = b.resolveTargetQuery(.{ .cpu_arch = .wasm32, .os_tag = .freestanding });
    const module = b.addModule("custom_std", .{
        .pic = true,
        .target = webTarget,
        .optimize = optimize,
    });
    module.addCSourceFiles(.{
        .language = .c,
        .files = &.{
            "src/base_str.c",
            "src/crypt.c",
            "src/file_ops.c",
            "src/gap_buffer.c",
            "src/hash_map.c",
            "src/linked_list.c",
            "src/log.c",
            "src/unicode_str.c",
        },
        .flags = &.{
            "-Wall",
            "-O2",
            "-std=c11",
            "-lm",
            "-DEMSCRIPTEN=1",
        },
    });
    module.addIncludePath(b.path("."));
    module.addIncludePath(b.path("./deps/utf8-zig/headers/"));
    module.addIncludePath(.{ .cwd_relative = "/usr/include/x86_64-linux-gnu" });
    module.addIncludePath(.{ .cwd_relative = "/usr/include" });

    module.addLibraryPath(b.path("./deps/utf8-zig/zig-out/lib/"));
    module.addObjectFile(b.path("./deps/utf8-zig/zig-out/lib/libwebutf8-zig.a"));
    const lib = b.addLibrary(.{
        .name = "custom_std",
        .linkage = linkage,
        .root_module = module,
    });
    b.installArtifact(lib);
}
