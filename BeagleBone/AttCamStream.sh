#!/bin/bash

gphoto2 --capture-movie --stdout | ffmpeg -f mjpeg -i pipe:0 -f mpeg1video -r 20 http://localhost:82/1234/320/240
