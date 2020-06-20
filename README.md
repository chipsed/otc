# 🔮 OTC Loader  / ![Windows](https://github.com/chipsed/otc/workflows/Windows/badge.svg?branch=master&event=push) /

----------------------------------------------------

Hello. This loader loads and initializes OTC in the CS:GO game.

-----------------------------------------------------

# FAQ
  - How clone this repository?
  > git clone https://github.com/chipsed/otc.git && cd otc && git submodule update --init --recursive
  -----
  - Everything worked out, but when i inject onetap, menu it does not render.
  > Enable multi-threaded rendering (in csgo) and then inject OTC. (If everything still does not work before, add a flag to disable d3x9 in the CS: GO startup parameters)
  ------
  - When you already fix what I need so much ??? I can’t play without it !!! (There should be a function name without which you cannot play)
  > First of all, we try to solve the most important problems. In TODO, you can see the order in which work is currently being performed.
  ----
   - The game crashes when I try inject OTC.
   > Make sure you have the latest version of OTC. If you inject an addon then try without it, very often it causes crashes. (Injector problems are also possible. Try using Process Hacker.)
  ----
  - I found this repository, but can't find OneTap source code.
  > Right. This is just a loader, that initializes & patch & invoke a binary file in game memory. You can watch/patch file here - [*Click me*](https://github.com/0x000cb/otc/blob/master/OTC/cpp/segment/Segment.cpp).
  
-----------------------------------------------------

# Last builds
  > [ZIP #1](https://github.com/chipsed/otc/releases/download/1.0/OTC.zip)

------------------------------------------------------

# Credits

  * [0x000cb](https://github.com/0x000cb) - (Project creator & reverse staff)
  * [HoShiMin](https://github.com/HoShiMin) - (Easy hook with HookLib :d)
  * [playday3008](https://github.com/playday3008) - Help with github & frequent pull requests.
  ------
  *  ♥ Community - Thank you for helping to develop and improve the project.
  *  ♥ toast, wnz, d3x - Thank you for starting all this. (p.s Original onetap crack authors)
  ------
  *  🛡️ flyingllama - Thank you for skeet level security.
