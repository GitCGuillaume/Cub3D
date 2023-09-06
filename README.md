# Projet Cub3D

Projet de raycasting, utilisant une librairie destinée à l'école 42.
Ce projet est inspiré d'un jeu utilisant cette même technologie, nommé Wolfenstein 3D.


Le raycasting permet de tracé des projections 3D à l'aide de rayon.

![raycast](https://github.com/GitCGuillaume/Cub3D/assets/34135668/675559ab-b67b-4b97-bfd3-2a5b59027d19)

Source : https://permadi.com/1996/05/ray-casting-tutorial-1/

Graphique simulant le tracer des rayons en utilisant π (pi)

![cub1](https://github.com/GitCGuillaume/Cub3D/assets/34135668/d2798dc8-d561-4959-8a8f-4b39b18ba147)
![cub2](https://github.com/GitCGuillaume/Cub3D/assets/34135668/0b79c86e-5542-46e5-840e-32b5fe2d1d41)
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
