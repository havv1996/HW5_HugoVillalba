import numpy as np
import matplotlib.pyplot as plt

dat_exp = np.loadtxt("RadialVelocities.dat")
dat_mod = np.loadtxt("Resultados.dat",delimiter=",")

R=dat_exp[:,0]
Vel_exp= dat_exp[:,1]

M_b = 0.9
M_d = 7776
M_h = 12093

b_b = 0.2497
b_d = 5.16
a_d = 0.3105
a_h = 64.3

def Funcion(R,M_b,M_d,M_h):
	
	return (M_b**(1.0/2.0))*R/((R*R)+(b_b*b_b))**(3.0/4.0) + (M_d**(1./2.))*R/((R*R)+(b_d+a_d)**2.0)**(3.0/4.0) + (M_h**(1./2.))/((R*R)+(a_h*a_h))**(1.0/4.0)

#def Recta(R,M_b,M_d):
	#return R*M_b + M_d
	
Vel_mod = Funcion(R,M_b,M_d,M_h)
plt.plot(R,Vel_mod, c="r")
#plt.plot(R,R*M_b + M_d)
plt.scatter(R,Vel_exp)
#plt.show()
plt.savefig("Grafica.pdf")
plt.close()

#plt.scatter(dat_mod[:,0],-np.log(dat_mod[:,3]))
#plt.show()
#plt.scatter(dat_mod[:,1],-np.log(dat_mod[:,3]))
#plt.show()
#plt.scatter(dat_mod[:,2],-np.log(dat_mod[:,3]))
#plt.show()
