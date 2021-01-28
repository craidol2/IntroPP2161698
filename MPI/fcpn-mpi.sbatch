#!/bin/bash

#SBATCH --partition=normal  # Nombre de la particion - Los nombres se obtienen con el comando sinfo
#SBATCH --job-name=mpi_fcpn # Nombre de la tarea a ejecutar - puede ser cualquiera
#SBATCH --nodes=2         # Cantidad de nodos a usar
#SBATCH --ntasks=2          # Numero de tareas a ejecutar
#SBATCH --cpus-per-task=4  # Numero de cores asignados a cada tarea
#SBATCH --output=output_mpi_fcpn.txt # Archivo de salida donde se encuentran los resultados de la ejecucion

module load devtools/mpi/openmpi/3.1.4    # Modulo que contiene el software a usar

if [ -n "$SLURM_CPUS_PER_TASK" ]; then
  omp_threads=$SLURM_CPUS_PER_TASK
else
  omp_threads=1
fi

mpirun -np 2 ./fcpn <<< 1000