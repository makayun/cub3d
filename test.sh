#!/bin/bash

make

./cub3D

./cub3D ./too.cub ./many.cub ./arguments.cub

./cub3D ./wrong_file.pdf

./cub3D no_path.cub

./cub3D ./doesnt_exist.cub

./cub3D ./wrong1_no_east.cub

./cub3D ./wrong2_too_big.cub

./cub3D ./wrong3_no_player.cub

./cub3D ./wrong4_two_players.cub

./cub3D ./wrong5_bad_asset.cub



