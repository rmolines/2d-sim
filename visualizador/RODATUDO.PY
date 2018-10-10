import argparse
import os
import matplotlib.pyplot as plt
import csv

parser = argparse.ArgumentParser()
parser.add_argument("-s", "-strategy", action="store", dest="s", help="seleciona tipo de paralelizacao:\
                    sequencial(seq), simd(simd, openmp(omp) ou best(best). results para rodar os testes \
                    e gerar os gráficos ao final. \
                    default is best", default="best")

parser.add_argument("-gui", help="1, mostra o visualizador, 0 não. deafult é 1 ", \
                    action="store", dest="gui", default=1)

parser.add_argument("-deltat", help="define um deltat para a simulacao. 0.01 se nao definido",\
                    action="store", dest="delta_t", default=0.01)

parser.add_argument("-model", help="escolhe o modelo simulacional a rodar. 0 para geometrico, 1 para elastico. padrao - 0",\
                    action="store", dest="model", default=0)

parser.add_argument("-nballs", help="escolhe o numero de bolinhas.",\
                    action="store", dest="n_balls", default=10)
                    

results = parser.parse_args()

print(results)

os.system("python create_input.py -n %d" % int(results.n_balls))

if(results.s == "simd"):
    os.system('cmake -DSTRATEGY=simd . && make \
        && ./visualizador %f %f %s %f<input' % (float(results.delta_t), float(results.gui), results.s, float(results.model)))
    
elif (results.s == "omp"):
    os.system('cmake -DSTRATEGY=omp . && make  \
        && ./visualizador %f %f %s %f <input' % (float(results.delta_t), float(results.gui), results.s, float(results.model)))

elif (results.s == "seq"):
    os.system('cmake -DSTRATEGY=seq . && make  \
        && ./visualizador %f %f %s %f <input' % (float(results.delta_t), float(results.gui), results.s, float(results.model)))

elif (results.s == "best"):
    os.system("cmake -DSTRATEGY=best . && make  \
        && ./visualizador %f %f %s %f <input" % (float(results.delta_t), float(results.gui), results.s, float(results.model)))

elif (results.s == "results"):
    command = 'cmake -DSTRATEGY=%s . && make  \
            && mprof run ./visualizador %f %f %s %f <input && mprof plot -o %s'


    os.system("python create_input.py -n %d" % (50))
    filename = './results-img/s=%s-n_balls=2500.jpg'

    os.system(command % ("best", float(results.delta_t), float(results.gui), "best", float(results.model), filename % ("best")))
    os.system(command % ("omp", float(results.delta_t), float(results.gui), "omp", float(results.model), filename % ("omp")))
    os.system(command % ("simd", float(results.delta_t), float(results.gui), "simd", float(results.model), filename % ("simd")))
    os.system(command % ("seq", float(results.delta_t), float(results.gui), "seq", float(results.model), filename % ("seq")))
    
    os.system("python create_input.py -n %d" % (70))
    filename = './results-img/-s=%s-n_balls=4900.jpg'

    os.system(command % ("best", float(results.delta_t), float(results.gui), "best", float(results.model), filename % ("best")))
    os.system(command % ("omp", float(results.delta_t), float(results.gui), "omp", float(results.model), filename % ("omp")))
    os.system(command % ("simd", float(results.delta_t), float(results.gui), "simd", float(results.model), filename % ("simd")))
    os.system(command % ("seq", float(results.delta_t), float(results.gui), "seq", float(results.model), filename % ("seq")))

    os.system("python create_input.py -n %d" % (90))
    filename = './results-img/-s=%s-n_balls=8100.jpg'
    os.system(command % ("best", float(results.delta_t), float(results.gui), "best", float(results.model), filename % ("best")))
    os.system(command % ("omp", float(results.delta_t), float(results.gui), "omp", float(results.model), filename % ("omp")))
    os.system(command % ("simd", float(results.delta_t), float(results.gui), "simd", float(results.model), filename % ("simd")))
    os.system(command % ("seq", float(results.delta_t), float(results.gui), "seq", float(results.model), filename % ("seq")))

    os.system("python create_input.py -n %d" % (110))
    filename = './results-img/-s=%s-n_balls=12100.jpg'
    os.system(command % ("best", float(results.delta_t), float(results.gui), "best", float(results.model), filename % ("best")))
    os.system(command % ("omp", float(results.delta_t), float(results.gui), "omp", float(results.model), filename % ("omp")))
    os.system(command % ("simd", float(results.delta_t), float(results.gui), "simd", float(results.model), filename % ("simd")))
    os.system(command % ("seq", float(results.delta_t), float(results.gui), "seq", float(results.model), filename % ("seq")))

    n_balls = [50**2, 70**2, 90**2, 110**2] 

    avg = [[0]*4]*4

    ind = -1
    for i in n_balls:
        ind += 1
        counter = 0
        sum = 0.0
        with open('./results/-s=best -gui=2 -model=0 -n_balls=%d.csv'%(i)) as csvfile:
            spamreader = csv.reader(csvfile)
            for row in spamreader:
                counter += 1
                sum += float(row[0])
            avg [0][ind] = sum/counter

    fig, ax = plt.subplots()
    ind = range(len(avg[0]))
    b, o, si, se = plt.bar(ind, avg[0])

    b.set_facecolor('r')
    o.set_facecolor('g')
    si.set_facecolor('b')
    se.set_facecolor('y')
    ax.set_xticks(ind)
    ax.set_xticklabels(['Best', 'OMP', 'SIMD', 'Seq'])
    ax.set_ylabel('Tempo(s)')
    ax.set_title('Tipo de compilação com 2500 bolinhas') 
    fig.savefig('./results-time/2500.jpg')   
    plt.close(fig)




    ind = -1
    for i in n_balls:
        ind += 1
        counter = 0
        sum = 0.0
        with open('./results/-s=omp -gui=2 -model=0 -n_balls=%d.csv'%(i)) as csvfile:
            spamreader = csv.reader(csvfile)
            for row in spamreader:
                counter += 1
                sum += float(row[0])

            avg [1][ind] = sum/counter

    fig, ax = plt.subplots()
    ind = range(len(avg[0]))
    b, o, si, se = plt.bar(ind, avg[1])

    b.set_facecolor('r')
    o.set_facecolor('g')
    si.set_facecolor('b')
    se.set_facecolor('y')
    ax.set_xticks(ind)
    ax.set_xticklabels(['Best', 'OMP', 'SIMD', 'Seq'])
    # ax.set_ylim([0, 100])
    ax.set_ylabel('Tempo(s)')
    ax.set_title('Tipo de compilação com 4900 bolinhas') 
    fig.savefig('./results-time/4900.jpg')   
    plt.close(fig)


    ind = -1
    for i in n_balls:
        ind += 1
        counter = 0
        sum = 0.0
        with open('./results/-s=simd -gui=2 -model=0 -n_balls=%d.csv'%(i)) as csvfile:
            spamreader = csv.reader(csvfile)
            for row in spamreader:
                counter += 1
                sum += float(row[0])

            avg [2][ind] = sum/counter

    fig, ax = plt.subplots()
    ind = range(len(avg[0]))
    b, o, si, se = plt.bar(ind, avg[2])

    b.set_facecolor('r')
    o.set_facecolor('g')
    si.set_facecolor('b')
    se.set_facecolor('y')
    ax.set_xticks(ind)
    ax.set_xticklabels(['Best', 'OMP', 'SIMD', 'Seq'])
    # ax.set_ylim([0, 100])
    ax.set_ylabel('Tempo(s)')
    ax.set_title('Tipo de compilação com 8100 bolinhas') 
    fig.savefig('./results-time/8100.jpg')   
    plt.close(fig)


    ind = -1
    for i in n_balls:
        ind += 1
        counter = 0
        sum = 0.0
        with open('./results/-s=seq -gui=2 -model=0 -n_balls=%d.csv'%(i)) as csvfile:
            spamreader = csv.reader(csvfile)
            for row in spamreader:
                counter += 1
                sum += float(row[0])

            avg [3][ind] = sum/counter
    
    fig, ax = plt.subplots()
    ind = range(len(avg[0]))
    b, o, si, se = plt.bar(ind, avg[3])

    b.set_facecolor('r')
    o.set_facecolor('g')
    si.set_facecolor('b')
    se.set_facecolor('y')
    ax.set_xticks(ind)
    ax.set_xticklabels(['Best', 'OMP', 'SIMD', 'Seq'])
    # ax.set_ylim([0, 100])
    ax.set_ylabel('Tempo(s)')
    ax.set_title('Tipo de compilação com 12100 bolinhas') 
    fig.savefig('./results-time/12100.jpg')   
    plt.close(fig)


    percent = [[0]*3]*4
    for i in range(len(avg)):
        percent [i][0] = (avg[i][0]/avg[i][3]) * 100
        percent [i][1] = (avg[i][1]/avg[i][3]) * 100
        percent [i][2] = (avg[i][2]/avg[i][3]) * 100

    fig, ax = plt.subplots()
    b, o, si = plt.bar(range(len(percent[0])),percent[0])

    b.set_facecolor('r')
    o.set_facecolor('g')
    si.set_facecolor('b')
    ax.set_xticks(ind)
    ax.set_xticklabels(['Best/Seq', 'OMP/Seq', 'SIMD/Seq'])
    ax.set_ylabel('Ganho de Desempenho (%)')
    ax.set_title('Tipo de compilação com 2500 bolinhas') 
    fig.savefig('./results-time/2500-percent.jpg')   
    plt.close(fig)

    fig, ax = plt.subplots()
    b, o, si = plt.bar(range(len(percent[1])),percent[1])

    b.set_facecolor('r')
    o.set_facecolor('g')
    si.set_facecolor('b')
    ax.set_xticks(ind)
    ax.set_xticklabels(['Best/Seq', 'OMP/Seq', 'SIMD/Seq'])
    ax.set_ylabel('Ganho de Desempenho (%)')
    ax.set_title('Tipo de compilação com 4900 bolinhas') 
    fig.savefig('./results-time/4900-percent.jpg')   
    plt.close(fig)

    fig, ax = plt.subplots()
    b, o, si= plt.bar(range(len(percent[2])),percent[2])

    b.set_facecolor('r')
    o.set_facecolor('g')
    si.set_facecolor('b')
    ax.set_xticks(ind)
    ax.set_xticklabels(['Best/Seq', 'OMP/Seq', 'SIMD/Seq'])
    ax.set_ylabel('Ganho de Desempenho (%)')
    ax.set_title('Tipo de compilação com 8100 bolinhas') 
    fig.savefig('./results-time/8100-percent.jpg')   
    plt.close(fig)

    fig, ax = plt.subplots()
    b, o, si= plt.bar(range(len(percent[3])),percent[3])

    b.set_facecolor('r')
    o.set_facecolor('g')
    si.set_facecolor('b')
    ax.set_xticks(ind)
    ax.set_xticklabels(['Best/Seq', 'OMP/Seq', 'SIMD/Seq'])
    ax.set_ylabel('Ganho de Desempenho (%)')
    ax.set_title('Tipo de compilação com 12100 bolinhas') 
    fig.savefig('./results-time/12100-percent.jpg')   
    plt.close(fig)