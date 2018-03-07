rm -f $2 $3 $4 $5

./norm_sst $1 $2
./segment $2 $3
./ind $2 $3 $4 $5
python plot_index_ext.py $4 $5
