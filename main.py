import os
os.environ['TF_CPP_MIN_LOG_LEVEL'] = '2' # supress warning

# calc
import numpy as np

#keras
print('[INFO] Loading keras')
from keras import backend as K
from keras.utils import np_utils
from keras.models import Sequential
from keras.layers import Dense, Dropout
from keras import optimizers

import input_voice
import extract_phoneme
import model

while True:
    input_voice.listen()
    extract_phoneme.extract()
    model.predict()