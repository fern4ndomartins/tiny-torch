set pagination off
set confirm off
set verbose off
set complaints 0

set print thread-events off
set print inferior-events off

set debuginfod enabled off
set startup-with-shell off

set $driver_loaded = 0

catch load libvulkan_radeon

commands
    silent
    set $driver_loaded = 1
    continue
end

run > /dev/null

if $driver_loaded
    printf "RADV loaded\n"
else
    printf "RADV NOT loaded\n"
end

quit
