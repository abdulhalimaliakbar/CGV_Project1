import speech_recognition as sr
from termcolor import colored
from os import path
import time
import os

# obtain audio from the microphone
r = sr.Recognizer()

def from_mic():
    with sr.Microphone() as source:
       input("Press [enter] to record.")
       print("[INFO] Get ready.")
       for i in range(3):
           print(3-i)
           time.sleep(1)
       print("[INFO] Listening...")
       audio = r.listen(source)

    # write audio to a WAV file
    wavpath = path.join(path.dirname(path.realpath(__file__)), "microphone-result.wav")
    with open(wavpath, "wb") as f:
       f.write(audio.get_wav_data())
       print("[INFO] Audio saved.")
    return audio

def from_wav(path):
    AUDIO_FILE = path.join(path.dirname(path.realpath(__file__)), "microphone-result.wav")
    with sr.AudioFile(AUDIO_FILE) as source:
        input("Press [enter] to record.")
        print("[INFO] Listening...")
        audio = r.record(source)


def listen():
    audio = from_mic()
    os.system('sox input_voice/microphone-result.wav -n stat 2>&1 | sed -n 2p')

    """
    with sr.AudioFile('english.wav') as source:
        audio = r.record(source) # read the entire audio file
    """

    try:
        # for testing purposes, we're just using the default API key
        # to use another API key, use `r.recognize_google(audio, key="GOOGLE_SPEECH_RECOGNITION_API_KEY")`
        # instead of `r.recognize_google(audio)`
        print("[INFO] Recognizing Speech.")
        transcript = r.recognize_google(audio)
        print(colored('[SUCCESS]', 'green'), "Google Speech Recognition thinks you said:")
        print('-' * len(transcript))
        print('"'+transcript+'"')
        print('-' * len(transcript))

        txtpath = path.join(path.dirname(path.realpath(__file__)), "microphone-result.txt")
        with open(txtpath, "w") as f:
            f.write(transcript)

        return True
    except sr.UnknownValueError:
        print(colored('[FAIL]', 'red'), "Google Speech Recognition could not understand audio")
    except sr.RequestError as e:
        print(colored('[FAIL]', 'red'), "Could not request results from Google Speech Recognition service; {0}".format(e))
    return False
