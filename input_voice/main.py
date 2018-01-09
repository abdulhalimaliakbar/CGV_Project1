print("[INFO] initializing, please wait.")
import speech_recognition as sr

# obtain audio from the microphone
r = sr.Recognizer()

with sr.Microphone() as source:
    input("Press any key to record.")
    print("[INFO] Listening...")
    audio = r.listen(source)
    print("[INFO] audio recorded.")

# write audio to a WAV file
#with open("microphone-results.wav", "wb") as f:
#    f.write(audio.get_wav_data())

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
    print("[SUCCESS] Google Speech Recognition thinks you said:")
    print('"'+transcript+'"')
except sr.UnknownValueError:
    print("Google Speech Recognition could not understand audio")
except sr.RequestError as e:
    print("Could not request results from Google Speech Recognition service; {0}".format(e))
