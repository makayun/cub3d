#!/bin/bash

set -v

make norm

./cub3D

./cub3D ./too.cub ./many.cub ./arguments.cub

./cub3D ./wrong_file.pdf

./cub3D no_path.cub

./cub3D ./doesnt_exist.cub

./cub3D ./wrong/1_no_east.cub

./cub3D ./wrong/2_too_big.cub

./cub3D ./wrong/3_no_player.cub

./cub3D ./wrong/4_two_players.cub

./cub3D ./wrong/5_bad_asset.cub

./cub3D ./wrong/6_wall_hole.cub

./cub3D ./wrong/7_bad_color.cub

./cub3D ./wrong/8_missing_color.cub