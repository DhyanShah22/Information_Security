import numpy as np

def char_to_num(char):
    if char == ' ':
        return 27 
    return ord(char.upper()) - ord('A') + 1

def num_to_char(num):
    if num == 27:
        return ' '
    return chr(num + ord('A') - 1)

def create_matrix(block, n):

    nums = [char_to_num(char) for char in block]
    return np.array(nums).reshape(n, n)

def example_keys(n):
    P = np.random.randint(1, 28, size=(n, n))  
    Q = np.random.randint(1, 28, size=(n, n))
    while np.linalg.det(Q) == 0:
        Q = np.random.randint(1, 28, size=(n, n))
    return P, Q

def encrypt(message, P, Q):
    n = P.shape[0]

    padded_message = message.upper()
    while len(padded_message) % (n * n) != 0:
        padded_message += ' ' 

    encrypted_blocks = []
    for i in range(0, len(padded_message), n * n):
        block = padded_message[i:i + n * n]
        A = create_matrix(block, n)
        B = np.dot(A + P, Q)  # B = (A + P)Q
        encrypted_blocks.append(B)
    
    return encrypted_blocks

def decrypt(encrypted_blocks, P, Q):
    Q_inv = np.linalg.inv(Q) 
    decrypted_blocks = []
    
    for B in encrypted_blocks:
        A = np.dot(B, Q_inv) - P  # A = BQ^{-1} - P
        decrypted_blocks.append(A)

    return decrypted_blocks

def matrix_to_message(blocks):
    message = ''
    for matrix in blocks:
        for row in matrix:
            message += ''.join(num_to_char(round(num)) for num in row)
    return message.strip()


message = input("Enter the plaintext:")
n = 3 

P, Q = example_keys(n)
print("Key Matrix P:\n", P)
print("Key Matrix Q:\n", Q)

encrypted_blocks = encrypt(message, P, Q)
print("\nCiphertext Matrices B:")
for i, B in enumerate(encrypted_blocks):
    print(f"Block {i + 1}:\n{B}")

encrypted_message = matrix_to_message(encrypted_blocks)
print("\nEncrypted Message:",encrypted_message)

decrypted_blocks = decrypt(encrypted_blocks, P, Q)
print("\nDecrypted Matrices A:")
for i, A in enumerate(decrypted_blocks):
    print(f"Block {i + 1}:\n{A}")

decrypted_message = matrix_to_message(decrypted_blocks)
print("\nDecrypted Message:", decrypted_message)
