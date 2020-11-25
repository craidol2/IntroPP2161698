# openmp

Dentro de la carpeta, se encuentran localizados los 5 archivos de la entrega de la evaluación 1:
- fcpn.c
- omp_fcpn.c
- fcpn.sbatch
- readme.md
- output_fcpn.txt


## Ejecución del programa:
En Guane:
1. gcc -fopenmp omp_fcpn.c -o fcpn -lm  //compilar
2. sbatch fcpn.sbatch  //ejecutar sbatch
3. Abrir el archivo   output_fcpn.txt    //ver salida
En local:
1. gcc -fopenmp omp_fcpn.c -o fcpn -lm   //compilar
2. ./fcpn <<<1000  //ejecutar (paso 1000 como paramero)