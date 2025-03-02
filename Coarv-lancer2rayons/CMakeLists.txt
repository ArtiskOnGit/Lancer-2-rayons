# CMakeList.txt : projet CMake pour Coarv-lancer2rayons, incluez la source et définissez
# la logique spécifique au projet ici.
#
cmake_minimum_required (VERSION 3.8)

# Ajoutez une source à l'exécutable de ce projet.
add_executable (Coarv-lancer2rayons "main.cpp" "main.h" "vec3.h" "color.h" "ray.h" "hittable.h" "sphere.h" "rtweekend.h" "interval.h" "camera.h")

# TODO: Ajoutez des tests et installez des cibles si nécessaire.
