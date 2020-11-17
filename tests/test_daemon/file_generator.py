from datetime import datetime
import hashlib
import random
import string

def random_string_generator(str_size: int):
    allowed_chars = string.ascii_letters + string.punctuation
    return ''.join(random.choice(allowed_chars) for x in range(str_size))


def generate_file(str_size):
    gen_str = random_string_generator(str_size)

    date_str = datetime.now().strftime("%Y-%m-%d-%H-%M-%S")
    filepath = "/tmp/" + date_str + ".txt"

    with open(filepath, "w") as f:
        f.write(gen_str)

    md5_sum = hashlib.md5(gen_str.encode('utf-8')).hexdigest()

    return filepath, md5_sum


size = 100000
filepath, md5_sum = generate_file(size)
print(filepath)
print(md5_sum)
