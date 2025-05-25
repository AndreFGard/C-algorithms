const std = @import("std");

const c = @cImport({
    @cInclude("unistd.h");
});

pub fn main() !void {
    var arena = std.heap.ArenaAllocator.init(std.heap.page_allocator);
    defer arena.deinit();
    //const allocator = arena.allocator();

    const argv = std.os.argv;
    const argc: c_int = @intCast(argv.len);
    var opt: c_int = c.getopt(argc, argv.ptr, "r:");
    const optind = &c.optind;

    var filter: [*c]const u8 = "";
    const defaultdir = "./";
    while (opt != -1) {
        switch (opt) {
            'r' => {
                filter = @as([*:0]u8, c.optarg);
                //const optarg = @as([*:0]u8, c.optarg);
                std.debug.print("Using format: {s}\n", .{filter});
            },
            '?' => {
                std.debug.print("unknown option: {c}\n", .{@as(u8, @intCast(c.optopt))});
            },
            else => unreachable,
        }
        opt = c.getopt(argc, argv.ptr, "r:");
    }
    const basedir = if (optind.* < argc)
        std.mem.span(argv[@intCast(optind.*)])
    else
        defaultdir;
    std.debug.print("your starting directory is argument {s}\n", .{@as([*:0]u8, @constCast(basedir))});
}
