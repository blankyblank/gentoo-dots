# dwl - dwm for Wayland

I added some scripts I use into the scripts directory. the autostart.sh for progrags I autostart on launch, and startw is the script that sets variables and launches dwl. It also has a function in it to set a couple things in the status bar. 

It has tofi-dwl which is just a script to get tofi working with dwl but using xargs to launch whatever is selected with /bin/sh -c. 

One called screenshot that uses grim and slurp to take screenshots and has 2 modes you can use, -s for manually selecting the area to screenshot, and -f for the full screen. Then it copies it to the clipboard. 

Another I threw in is called backlight.sh this one you might need some extra effort to get working on you system if you want to use it. it either raises or lowers your backlight -u for up -d for down. It's made for my system, so the /sys file you have to use might be slightly different for yours depending on your hardware. You will also need the right permissions to adjust the backlight which is what the backlight.rules file is for. It needs to be in /etc/udev/rules.d/ and you will probably need to reboot if you didn't already have these set.

The keybinds will need to be changed to whatever you want to actually use. Most of them are set to scripts on my system to launch the actual things I want. I have a few to launch terminals or chat applications in scratchpads. Look into how the dwl scratchpad patch works for an explanation on how to adjust those to whatever you want to use. I also have the terminal set to foot. So it would be a good idea to either install foot, or change that to another terminal before launching it. Super+Shift+c kills dwl with how I have it set up, Super+q kills windows, and Super+enter launches a terminal.
