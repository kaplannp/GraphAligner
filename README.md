# GraphAligner

Program for aligning long error-prone reads to genome graphs. For simple usage, see ["Running the alignment pipeline"](#running-the-alignment-pipeline). For a description of the bitvector algorithm, see https://www.biorxiv.org/content/early/2018/05/15/323063

### Installation

- Install miniconda https://conda.io/docs/user-guide/install/index.html
- `git clone https://github.com/maickrau/GraphAligner.git`
- `git submodule update --init --recursive`
- `conda env create -f CondaEnvironment.yml`
- `source activate GraphAligner`
- `make all`

### Running the alignment pipeline

- Copy the folder Snakefiles/align_with_mummer somewhere, call it run_folder
- Acquire a graph and save it in run_folder/input/
- Acquire reads and save them in run_folder/input/
- Edit run_folder/config.yaml
  - Add the path of the repository folder
  - Add the input file names
  - Optionally edit the aligner parameters
- Run `source activate GraphAligner`
- Run `snakemake --cores [number of threads] all` in run_folder
- The output will be in run_folder/output/

### Output

A summary of the alignment is in `output/stats_[readfile]_[graphfile].txt`. Individual alignments are in the files `output/aln_[readfile]_[graphfile]_all.gam`, `output/aln_[readfile]_[graphfile]_selected.gam` and `output/aln_[readfile]_[graphfile]_full_length.gam`. To view the `.gam` files, use [vg](https://github.com/vgteam/vg/). 

The file `_all.gam` contains all found alignments, usually including multiple incompatible alignments per read, eg. one base pair is aligned to multiple parts of the graph. The file `_selected.gam` is a set of non-overlapping alignments, so each read base pair is aligned to at most one location in the graph. The file `_full_length.gam` contains alignments where the entire read was aligned to one location.

### Parameters

- `-b` alignment bandwidth. Unlike linear alignment, this is the score difference between the minimum score in a row and the score where a cell falls out of the band. Values should be between 1-35.
- `-B` extra bandwidth. If a read cannot be aligned with the aligner bandwidth, switch to extra bandwidth at the problematic location. Values should be between 1-35.
- `-C` bandwidth limit. Determines how much effort the aligner spends on tangled areas. Higher values use more CPU and memory and have a higher chance of aligning through tangles. Lower values are faster but might return an inoptimal or a partial alignment. Use for complex graphs (eg. de Bruijn graphs of mammalian genomes) to limit the runtime in difficult areas. Values should be between 1'000 - 500'000.
- `-l` low memory mode. Uses a lot less memory but runs a bit slower.
- `-u` unsafe heuristics. Speeds up alignment in some cases but might lead to inoptimal results.

Suggested example parameters:
- Variation graph: `-b 35`
- RNA splice graph: `-b 35`
- Human de Bruijn graph: `-b 5 -B 10 -C 1000 -l -u`
- Bacterial de Bruijn graph: `-b 10 -B 20`

The parameters below are only relevant if manually running GraphAligner. If you are using the snakefile, you shouldn't do anything with these

- `-g` input graph. Format .gfa / .vg
- `-f` input reads. Format .fasta / .fastq / .fasta.gz / .fastq.gz
- `-s` input seeds. Format .gam
- `-t` number of threads
- `-a` output file name. Format .gam
- `-A` maximum number of output alignments. Outputs only the n best non-overlapping alignments.
