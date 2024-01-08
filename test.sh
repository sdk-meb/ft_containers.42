SEED="1047552"

make diff

exec time ./org_cs $SEED > "./org_out" 2> "./org_err" &\
exec time ./rec_cs $SEED > "./rec_out" 2> "rec_err"