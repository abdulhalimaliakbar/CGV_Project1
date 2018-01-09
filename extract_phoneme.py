#!/usr/bin/env python3
import math
import os

DEBUG = False
CACHE = False
QUIET = True

def system(cmd):
    if not CACHE:
        if DEBUG:
            print(cmd)
        else:
            os.system(cmd)

def print_debug(msg):
    if not QUIET:
        print(msg)

def filter_zip(name):
    if name.find('.zip') != -1:
        return False
    return True


def filter16_textgrid(filename):
    name, ext = os.path.splitext(filename)
    if ext != '.wav':
        return False
    if filename.find('textgrid') != -1 or filename.find('16000') != -1:
        return False
    return True

def process_textgrid(path, duration):
    f = open(path)
    line = True
    while line:
        line = f.readline()
        if line.find("phone") != -1:
            break

    start_time = float(f.readline().rstrip('\n'))
    end_time = float(f.readline().rstrip('\n'))
    number = f.readline().rstrip('\n')

    phoneme_list = []
    print("phoneme number:{}".format(number))
    phoneme_list.append({"start": 0, "end": start_time, "val": "NOP"})
    for i in range(int(number)):
        s = f.readline().rstrip('\n')
        e = f.readline().rstrip('\n')
        p = f.readline().rstrip('\n').replace('"', '')
        phoneme_list.append({"start": float(s), "end": float(e), "val": p})
    phoneme_list.append({"start": end_time, "end": duration, "val": "NOP"})
    return phoneme_list

def get_frame_num(path):
    return len(os.listdir(path))

def get_duration(path):
    f = open(path)
    f.readline()
    result = f.readline().rstrip('\n')[len("Length (seconds):"):]
    f.close()
    return float(result)

def save_phonemes(ppath, phonemes, duration):
    f = open(ppath, 'w')
    p_i = 0
    frame_num = int(math.ceil(duration / 0.04))
    for i in range(frame_num):
        sample_time = i * 0.04
        if (sample_time >= phonemes[p_i]['end']):
            p_i += 1
        f.write(phonemes[p_i]['val']+'\n')
    f.close()
    print_debug("saved: {}".format(ppath))

def textgrid_to_phoneme(wavpath, textgridpath, outputpath):
    system("sox {} -n stat 2> /tmp/duration".format(wavpath))
    duration = get_duration('/tmp/duration')
    phonemes = process_textgrid(textgridpath, duration)
    save_phonemes(outputpath, phonemes, duration)

def wav_to_phoneme(wavepath, transpath, outputpath):
    system('python2 ../p2fa/align.py {} {} /tmp/textgrid'.format(wavepath, transpath))
    textgrid_to_phoneme(wavepath, '/tmp/textgrid', outputpath)

print('[INFO] resampling audio')
system('sox input_voice/microphone-result.wav -r 16000 input_voice/microphone-result-resample-16000.wav')
print('[INFO] converting audio to phoneme sequence')
wav_to_phoneme('input_voice/microphone-result-resample-16000.wav', 'input_voice/microphone-result.txt', 'input_voice/microphone-result.phoneme')
