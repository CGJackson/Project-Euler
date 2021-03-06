import urllib.request

origin = (0.0,0.0)

def above_intersection(x,r1,r2):
    '''
    Takes 3 points on a 2d plane as input

    returns True if x is above the line joining r1 and r2
    '''
    m1 = r1[0]-r2[0]
    m2 = r1[1]-r2[1]
    c = r1[1]*r2[0] -r1[0]*r2[1]
    return x[1]*m1 > x[0]*m2 - c

def cyclic_permutations(l):
    '''
    generates all cyclic permutations of a list 
    '''
    l = list(l)
    for _ in l[:]:
        yield l
        temp = l.pop(0)
        l.append(temp)


def inside_triangle(x,r1,r2,r3):
    return all(above_intersection(a,b,c) == above_intersection(x,b,c)
            for a,b,c in cyclic_permutations([r1,r2,r3]))

def parse_data_line(line):
    data = [float(n) for n in line.decode('utf-8').split(',')]
    return tuple((data[i], data[i+1]) for i in range(0,6,2))
    
if __name__ == '__main__':
    data_address = 'https://projecteuler.net/project/resources/p102_triangles.txt'
    triangles = map(parse_data_line,urllib.request.urlopen(data_address))

    triangles_containing_origin = 0

    for p1,p2,p3 in triangles:
        if inside_triangle(origin,p1,p2,p3):
            triangles_containing_origin += 1

    print('The number of triangles containing the origin is',triangles_containing_origin)


