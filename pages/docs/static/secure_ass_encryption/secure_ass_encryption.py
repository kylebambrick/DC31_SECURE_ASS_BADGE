flag = bytes("HIDE_THIS_FROM_THEM".encode('utf-8'))
secure_ass_encryption = bytes("ASS".encode('utf-8'))
ciphertext = ""

for i in range(len(flag)):
	ciphertext += chr(secure_ass_encryption[i % 3])
	ciphertext += chr(flag[i] ^ secure_ass_encryption[i % 3]) 

print(bytes(ciphertext.encode('utf-8')))
