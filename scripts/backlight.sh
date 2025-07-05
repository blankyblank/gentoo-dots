#!/usr/bin/sh

current="$(cat /sys/class/backlight/amdgpu_bl0/brightness)"

backlight_down() {
  if [ $current -gt 0 ]; then 
    down=$(($current-10))
    echo $down > /sys/class/backlight/amdgpu_bl0/brightness
  else 
      exit 0
  fi
}

backlight_up() {
  if [ $current -lt 225 ]; then 
      up=$(($current+10))
      echo $up > /sys/class/backlight/amdgpu_bl0/brightness
  else 
      exit 0
  fi
}

while getopts "du" flag; do
  case $flag in
    d)
    backlight_down
    ;;
    u)
    backlight_up
    ;;
  esac
done
