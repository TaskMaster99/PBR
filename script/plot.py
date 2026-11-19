#!/usr/bin/env python3

import math
from functools import reduce

import matplotlib.pyplot as plt
import time
import numpy as np
import pandas as pd


def MSESphereSamplinglPlotting():
    data = pd.read_csv("data/sphere_sampling.csv", sep=';')

    x              = data['x']
    y              = data['y']
    z              = data['z']
    fig, ax        = plt.subplots(figsize=(10,10), subplot_kw={"projection": "3d"})
    
    ax.scatter(xs=x, ys=y,zs=z, s=0.75, color='red')
    ax.set_xlabel("X")
    ax.set_ylabel("Y")
    ax.set_zlabel("Z")
    ax.set_title(f"Uniform sample of sphere with Monte Carlo Estimator")

    fig.savefig("data/img/uniform_volum_sphere.png")

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
    MSESphereSamplinglPlotting()



