# MPI

Dentro de la carpeta, se encuentran localizados los 5 archivos de la entrega de la evaluación 2:
- mpi_fcpn.c
- fcpn-mpi.sbatch
- readme.md
- output_mpi_fcpn.txt
- tiempos_ejecucion.md

## Ejecución del programa:
#### En Guane: 
- module load devtools/mpi/openmpi/3.1.4
- mpicc -lm mpi_fcpn.c -o fcpn   //compilar
- sbatch fcpn-mpi.sbatch   //ejecutar
- Revisar archivo output_mpi_fcpn.txt   //salida