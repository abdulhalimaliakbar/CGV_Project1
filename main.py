import os

os.system('python3 input_voice/main.py')
print("[INFO] Process audio")
os.system('python3 extract_phoneme.py')
