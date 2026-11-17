#!/usr/bin/env python3

import math
from functools import reduce

import matplotlib.pyplot as plt
import time
import numpy as np
import pandas as pd


def MSESphereIntegralPlotting():

    data = pd.read_csv("data/mce_sphere_integral.csv", sep=';')

    size = data['size']
    idealMSE = data["idealMSE"]
    idealRMSE = data["idealRMSE"]
    currentMSE = data["MSE"]
    currentRMSE = data["RMSE"]

    fig0, ax0 = plt.subplots(figsize=(8,8))

    ax0.set_title('MSE of Monte Carlo Sphere Integral Sampling Method')
    ax0.plot(size, currentMSE, color='orange', label='MSE with Uniform Sampling')
    ax0.plot(size, idealMSE, color='green', label = 'Ideal MSE')

    ax0.set_xlabel('n sample')
    ax0.set_ylabel('MSE')
    ax0.set_xscale('log')
    ax0.set_yscale('log')
    ax0.legend()
    fig0.savefig("data/img/MSE.png")
    plt.close(fig0)


    fig1, ax1 = plt.subplots(figsize=(8,8))

    ax1.set_title('RMSE of Monte Carlo Sphere Integral Sampling Method')
    ax1.plot(size, currentRMSE, color='orange', label='RMSE with Uniform Sampling')
    ax1.plot(size, idealRMSE, color='green', label='Ideal RMSE')

    ax1.set_xlabel('n sample')
    ax1.set_ylabel('RMSE')
    ax1.set_xscale('log')
    ax1.set_yscale('log')
    ax1.legend()
    fig1.savefig("data/img/RMSE.png")
    plt.close(fig1)



if __name__ == '__main__':
    MSESphereIntegralPlotting()



