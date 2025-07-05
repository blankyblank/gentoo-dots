#!/bin/sh

cliphist wipe &
wl-paste --type text --watch cliphist store &
wl-paste --type image --watch cliphist store &
bgstart &
swayidle &
fnott &
dbus-update-activation-environment --systemd WAYLAND_DISPLAY XDG_CURRENT_DESKTOP=wlroots &
0<&-
