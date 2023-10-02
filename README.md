# Projet Cub3D

Projet de raycasting, utilisant une librairie destinée à l'école 42.
Ce projet est inspiré d'un jeu utilisant cette même technologie, nommé Wolfenstein 3D.


Le raycasting permet de tracé des projections 3D à l'aide de rayon.

![raycast](https://github.com/GitCGuillaume/Cub3D/assets/34135668/4b41448c-af28-4a39-8d7c-15c5264db77b)

Source : https://permadi.com/1996/05/ray-casting-tutorial-1/

Graphique simulant le tracé des rayons en utilisant π (pi)

![cub1](https://github.com/GitCGuillaume/Cub3D/assets/34135668/573a85ea-ede2-4d6b-89b9-1615ac891dcc)
![cub2](https://github.com/GitCGuillaume/Cub3D/assets/34135668/25404c32-6ff6-4704-8e15-6a4340de8599)

Image gérant la collision avec les murs.

Ce projet pourrait avoir besoin de certains paquets:
>apt-get install libxext-dev libbsd-dev
>
>apt-get install make

Compilation
>make all
>
>make bonus

Lancer le programme dans un terminal de commande linux
>Sans collision : ./cub3D maps/map.cub
>
>Avec collision : ./cub3D_bonus maps/map.cub
