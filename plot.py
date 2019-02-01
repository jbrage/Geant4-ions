import matplotlib.pyplot as plt
import numpy as np


def histogramfilename(z_particle = 1, hist_type = 'dose'):
    if hist_type == 'total_dose':
        return "build/histograms/_h1_total_dose.csv"
    else:
        return "build/histograms/_h1_{:d}_z_{}.csv".format(z_particle, hist_type)


def read_histogram_header():
    '''
    Load the histogram dimensions from the file
    '''
    key = "#axis fixed"
    with open(histogramfilename(), 'r') as myfile:
        for line in myfile:
            if key in line:
                ar = line.split(" ")
                min_cm = float(ar[-2])
                max_cm = float(ar[-1])
                return min_cm, max_cm


MIN_depth_cm, MAX_depth_cm = read_histogram_header()


def load_histogram(z_particle = 1, hist_type='dose'):
    '''
    Load the histogram; the name corresponds to the atomic number
    including all isotopes
    '''
    try:
        fname = histogramfilename(z_particle, hist_type)

        entries, scored_quantity = np.genfromtxt(
            fname,
            # comments = '#',
            unpack = True,
            skip_header = 8,  # NaNs and 0
            skip_footer = 1,  # 0
            dtype = float,
            delimiter = ",",
            usecols = [0, 1])

        NaNs = np.where(entries == 0)
        entries[NaNs] = np.nan

        depth_cm = np.linspace(MIN_depth_cm, MAX_depth_cm, len(scored_quantity))
    except:
        scored_quantity = []; depth_cm = []
    return depth_cm, scored_quantity


def load_fLET(z_particle):
    '''
    Compute the fluence-averaged LET as
    \sum energy [keV] / \sum track lengths [um]
    '''
    depth_cm, energy_deposition_keV = load_histogram(z_particle, 'dose')
    _, fluence_um = load_histogram(z_particle, 'fluence')
    zeros = np.where(fluence_um == 0)
    fluence_um[zeros] = np.nan  # dont kill the baby
    fLET_keV_um = energy_deposition_keV/fluence_um
    return depth_cm, fLET_keV_um


def main(n):

    # label dictionary
    z_dic = {1:"H", 2:"He", 3:"Li", 4:"Be", 5:"B", 6:"C", 7:"N", 8:"O", 9:"F"}

    # load colors
    prop_cycle = plt.rcParams['axes.prop_cycle']
    colors = prop_cycle.by_key()['color']

    # total depth dose curve
    depth_cm, total_dose = load_histogram(hist_type = 'total_dose')
    max_dose = max(total_dose)
    total_dose /= max_dose

    fig, (ax1, ax2, ax3) = plt.subplots(3, 1, sharex=True)
    fig.subplots_adjust(wspace = 0.01, hspace = 0.12)

    min_y2 = 1e-0

    # plot the total depth dose curve
    ax1.plot(depth_cm, total_dose, label = "Total dose", color = 'k', ls = '--')

    # iterate through the chosen isotopes of ions with charge z
    for i, ion in enumerate(range(1,n)):

        label = z_dic[ion]
        kwargs = {'color' : colors[i], 'label' : label}

        # depth dose curve
        depth_cm, dose = load_histogram(ion)
        dose /= max_dose
        ax1.plot(depth_cm, dose,**kwargs)

        # dose contribution [%]
        percent_dose = dose/total_dose*100
        below = np.where(percent_dose < min_y2)
        percent_dose[below] = min_y2
        ax2.plot(depth_cm, percent_dose, **kwargs)
        # ax2.plot(depth_cm, dose, **kwargs)

        # fluence-averaged LET
        _, fLET = load_fLET(ion)
        ax3.plot(depth_cm, fLET, **kwargs)

    ax2.set_yscale('log')
    ax3.set_yscale('log')

    ax1.legend(loc='upper center', bbox_to_anchor=(0.5, 1.6),
              ncol=5, fancybox=True)

    ax1.set_ylabel("Dose [arb. units]")
    ax2.set_ylabel(r"Dose [$\%$]")
    ax3.set_ylabel(r"LET$_\Phi$ [keV/µm]")
    ax3.set_xlabel("Depth [cm]");

    ax1.set_xlim([MIN_depth_cm, MAX_depth_cm])
    ax1.set_ylim([0, 1.05])

    ax2.set_xlim([MIN_depth_cm, MAX_depth_cm])
    ax2.set_ylim([min_y2, 100])
    # ax2.set_ylim([0, 0.02])

    fig.savefig('depth_doses.pdf', bbox_inches = 'tight')



if __name__ == "__main__":
    main(n = 9)
