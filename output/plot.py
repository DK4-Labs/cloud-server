import math
import matplotlib.pyplot as plt
from pandas import *
from statistics import mean


# def erlang_probability(A, m):
#     numerator = (A**m) / math.factorial(m)
#     sum = 0

#     for n in range(m+1):
#         sum += (A**n)/math.factorial(n)

#     return(numerator/sum)


def main():
    # channels = 19
    # offered_load = 1

    # CHANNELS = []

    # PB_all = []

    # for i in range(19):
    #     CHANNELS.append(i)

    # for i in range(1, 10):
    #     for j in range(1, channels+1):
    #         PB = erlang_probability(i, j)
    #         PB_all.append(PB)

    # chunked_list = list()
    # chunk_size = 19

    # for i in range(0, len(PB_all), chunk_size):
    #     chunked_list.append(PB_all[i:i+chunk_size])

    # denom_sum = 0

    # for i in range(channels):
    #     numerator = (offered_load**channels)/math.factorial(channels)
    #     denom = (offered_load**i)/math.factorial(i)
    #     denom_sum = denom_sum + denom
    #     PB_1.append(numerator/denom_sum)

    # reading CSV file
    data = read_csv("output/sim_data_device1.csv",
                    usecols=[2], names=['Arrival Rate'], header=None)
    data2 = read_csv("output/sim_data_device2.csv",
                     usecols=[4], names=['delay 2'], header=None)
    data1 = read_csv("output/sim_data_device1.csv",
                     usecols=[4], names=['delay 1'], header=None)
    # data2 = read_csv("output/sim_data_channel3.csv",
    #                  usecols=[2], names=['data1'], header=None)
    # data3 = read_csv("output/sim_data_channel4.csv",
    #                  usecols=[2], names=['data1'], header=None)
    # data4 = read_csv("output/sim_data_channel5.csv",
    #                  usecols=[2], names=['data1'], header=None)
    # data5 = read_csv("output/sim_data_channel6.csv",
    #                  usecols=[2], names=['data1'], header=None)
    # data6 = read_csv("output/sim_data_channel7.csv",
    #                  usecols=[2], names=['data1'], header=None)
    # data7 = read_csv("output/sim_data_channel8.csv",
    #                  usecols=[2], names=['data1'], header=None)

    # converting column data to list
    list = data['Arrival Rate'].tolist()
    list1 = data2['delay 2'].tolist()
    list2 = data1['delay 1'].tolist()
    # list3 = data3['data1'].tolist()
    # list4 = data4['data1'].tolist()
    # list5 = data5['data1'].tolist()
    # list6 = data6['data1'].tolist()
    # list7 = data7['data1'].tolist()

    # list_all = list + list1 + list2 + list3 + list4 + list5 + list6 + list7
    # newlist = []
    # chunk_size = 3

    # for i in list:
    #     throughput = i*(math.exp(-abs(2*int(i))))
    #     newlist.append(throughput)

    # for i in range(0, len(list_all), chunk_size):
    #     chunked_list.append(list_all[i:i+chunk_size])

    # print(chunked_list)

    # temp = []
    # for i in chunked_list:
    #     temp.append(mean(i)/60])

    # final= []
    # for i in range(0, len(temp), 6):
    #     final.append(temp[i: i+6])

    # print(final)

    # offered= [3, 6, 9, 12, 15, 18]

    plt.plot(list, list1, label="Device 1")
    plt.plot(list, list2, label="Device 2")

    print(list)

    # print(newlist)
    # plt.plot(offered, final[1], label="Channel = 2")
    # plt.plot(offered, final[2], label="Channel = 3")
    # plt.plot(offered, final[3], label="Channel = 4")
    # plt.plot(offered, final[4], label="Channel = 5")
    # plt.plot(offered, final[5], label="Channel = 6")
    # plt.plot(offered, final[6], label="Channel = 7")
    # plt.plot(offered, final[7], label="Channel = 8")

    # plt.legend()
    plt.xlabel("Arrival rate")
    plt.ylabel("Mean Delay")
    plt.title("Mean Delay vs Arrival Rate")
    plt.legend()
    plt.show()


if __name__ == "__main__":
    main()
