def above_intersection(x,r1,r2):
    '''
    Takes 3 points on a 2d plane as input

    returns True if x is above the line joining r1 and r2
    '''
    m1 = r1[0]-r2[0]
    m2 = r1[1]-r2[1]
    c = r1[1]*r2[0] -r1[0]*r2[1]
    return x[1]*m1 > x[0]*m2 + c

def cyclic_permutations(l):
    '''
    generates all cyclic permutations of a list 
    '''
    for x in l[:]:
        yield l
        temp = l.pop(0)
        l.append(temp)


def inside_triangle(x,r1,r2,r3):
    return all(above_intersection(a,b,c) == above_intersection(x,b,c)
            for a,b,c in cyclic_permutations([r1,r2,r3]))
