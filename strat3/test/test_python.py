
import sys

sys.path.append('../../strat3-build/test_python.py')
sys.path.append('/home/midgard/Dropbox/project/Strat3/strat3-build')

import libpyStrat3 as mat

a = mat.Zero(10, 10)
# a = mat.Matrix(10, 10)

print a[0:5, 0:5]
# print str(a)


# a = mat.Ones(10, 10)
# print a / 2.0


# check if boost::python kept the idea of pointers
b = mat.MatrixManager()

b.append("myMat", a)

b['myMat'] = mat.Ones(4, 4)

print a
# and it did !!

c = mat.MatrixQuery(b, 0, 2)

print c.cols("myMat")
print c.min()
print c.max()
print c.size()
print c.middle_rows("myMat", 0, 1)


d = mat.DataManager()
d.append("myMan", b)

print d["myMan"]["myMat"]

solver_test = mat.Random(4, 4)
b = mat.Random(4, 1)
 
print solver_test
print ' '
print mat.PartialLU(solver_test).solve(b)
print ' '
print solver_test.full_lu().solve(b)


#import libMatrixQuery as mq
#d = mq.MatrixManager()
#d.append("myMat", a)
#print d["myMat"]




