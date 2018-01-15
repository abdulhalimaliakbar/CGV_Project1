# calc
import numpy as np

#keras
from keras import backend as K
from keras.utils import np_utils
from keras.models import Sequential
from keras.layers import Dense, Dropout
from keras import optimizers

from os import path

# parameters
P = ["EH2", "K", "S", "L", "AH0", "M",
 "EY1", "SH", "N", "P", "OY2", "T",
 "OW1", "Z", "W", "D", "AH1", "B",
 "EH1", "V", "IH1", "AA1", "R", "AY1",
 "ER0", "AE1", "AE2", "AO1", "NG", "G",
 "IH0", "TH", "IY2", "F", "DH", "IY1",
 "HH", "UH1", "IY0", "OY1", "OW2", "CH",
 "UW1", "IH2", "EH0", "AO2", "AA0", "AA2",
 "OW0", "EY0", "AE0", "AW2", "AW1", "EY2",
 "UW0", "AH2", "UW2", "AO0", "JH", "Y",
 "ZH", "AY2", "ER1", "UH2", "AY0", "ER2",
 "OY0", "UH0", "AW0", "br", "cg", "lg", "ls", "ns", "sil", "sp", "NOP"]
P_num = len(P)
FACES_FOLDER = r'/home/jxcode/project/face'
PHONEMES_FOLDER = r"/home/jxcode/project/phonemes"

Kx = 31
Ky = 5
PAD_X = (Kx-1) // 2
PAD_Y = (Ky-1) // 2
batch_size = 100
hidden_unit_num = 3000 # per layer
dropout_rate = 0.5
INPUT_DIM = Kx*len(P) # windows size, phoneme catagory number
OUTPUT_DIM = Ky*36*2 # window size, point number, x, y
OUTPUT_DIM = Ky*16 # after pca
CENTER_NODE = 30 # point that center


def get_X_raw(phonemes_path):
    X_raw = []
    with open(phonemes_path) as f:
        lines = f.readlines()
        for line in lines:
            line = line.rstrip('\n') # sp
            one_hot = np.zeros((len(P)))
            one_hot[P.index(line)] = 1;
            X_raw.append(one_hot)
        X_raw = np.array(X_raw)
    # each row of X_raw is one_hot phoneme
    # row number = frame number
    return X_raw

def pad_raw(raw, WSIZE):
    W_HALF = (WSIZE-1) // 2
    raw_padded = np.pad(raw, ((W_HALF, W_HALF), (0,0)), 'edge')
    result = []
    for i in range(len(raw)):
        result.append(raw_padded[i:i+WSIZE].flatten())
    result = np.array(result)
    return result

def smooth(x,window_len=3,window='hanning'):

    if x.ndim != 1:
        print("bad, 1")

    if x.size < window_len:
        print("bad, 2")


    if window_len<3:
        return x


    if not window in ['flat', 'hanning', 'hamming', 'bartlett', 'blackman']:
        print("bad, 3")


    s=np.r_[x[window_len-1:0:-1],x,x[-2:-window_len-1:-1]]
    #print(len(s))
    if window == 'flat': #moving average
        w=np.ones(window_len,'d')
    else:
        w=eval('np.'+window+'(window_len)')

    y=np.convolve(w/w.sum(),s,mode='valid')
    return y

def predict():
    print('[INFO] Predicting...')
    phonemepath = path.join(path.dirname(path.realpath(__file__)), 'microphone-result.phoneme')
    xraw = get_X_raw(phonemepath)
    xpad = pad_raw(xraw, Kx)

    model = Sequential([
        Dense(hidden_unit_num, input_dim=INPUT_DIM, activation='tanh'),
        Dense(hidden_unit_num, activation='tanh'),
        Dense(hidden_unit_num, activation='tanh'),
        Dense(OUTPUT_DIM),
    ])

    weightpath = path.join(path.dirname(path.realpath(__file__)), 'model_weights.h5')
    model.load_weights(weightpath)

    y = model.predict(xpad)
    y = y[:, 16*2:16*3]
    print(y.shape)
    for i, seq in enumerate(y.T):
        with open('sequence' + str(i), 'w') as f:
            smooth_seq = smooth(np.repeat(seq, 4), 11, 'flat')
            for s in smooth_seq:
                f.write(str(s)+'\n')

#adam = optimizers.Adam(lr=1e-6)
#model.compile(loss='mean_squared_error', optimizer=adam)