import os
from sys import argv

test_id = 0
if len(argv) == 2:
    test_id = int(argv[1])

print "# test", test_id

# normal test
if test_id == 0:
    num_periods = 3
    prod_normal = 3
    cost_prod_normal = 3

    flag_extra_shift = 1
    extra_shift = 3
    cost_extra_shift = 3

    flag_subcon = 1
    subcon = 3
    cost_subcon = 3

    initial_stock = 12
    cost_initial_stock = 3

    flag_delay = 1
    cost_delay = 3

    demand = []
    for i in range(num_periods):
        d_in_i = i + 1
        demand.append(d_in_i)
# teste com delay
elif test_id == 1:
    num_periods = 3
    prod_normal = 3
    cost_prod_normal = 1

    flag_extra_shift = 1
    extra_shift = 4
    cost_extra_shift = 10

    flag_subcon = 1
    subcon = 4
    cost_subcon = 20

    initial_stock = 0
    cost_initial_stock = 0

    flag_delay = 1
    cost_delay = 5

    demand = []
    for i in range(num_periods):
        d_in_i = 4 - i
        demand.append(d_in_i)
# teste com sub contract + extra shift + delay
elif test_id == 2:
    num_periods = 5
    prod_normal = 2
    cost_prod_normal = 1

    flag_extra_shift = 1
    extra_shift = 2
    cost_extra_shift = 20

    flag_subcon = 1
    subcon = 1
    cost_subcon = 10

    initial_stock = 0
    cost_initial_stock = 0

    flag_delay = 1
    cost_delay = 30

    demand = []
    for i in range(num_periods):
        d_in_i = 6 - i
        demand.append(d_in_i)

else:
    print '# teste', test_id, 'nao implementado'
    exit()

cmd = 'echo \'' + str(num_periods) + ' ' + str(prod_normal) + ' ' + str(cost_prod_normal)
cmd += ' ' + str(flag_extra_shift)
if flag_extra_shift:
    cmd += ' ' + str(extra_shift) + ' ' + str(cost_extra_shift)

cmd += ' ' + str(flag_subcon)
if flag_subcon:
    cmd += ' ' + str(subcon) + ' ' + str(cost_subcon)

cmd += ' ' + str(initial_stock) + ' ' + str(cost_initial_stock)

cmd += ' ' + str(flag_delay)
if flag_delay:
    cmd += ' ' + str(cost_delay)

for d in demand:
    cmd += ' ' + str(d)

cmd += '\' | ./mpp '

print cmd
os.system(cmd)
