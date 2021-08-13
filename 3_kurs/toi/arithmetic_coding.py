"""
Арифметическое кодирование
Программная реализация сжатия текстовых данных без потери информации с использованием арифметического кодирования.
"""
def float2bin(x, eps=1e-9):
    res = ''
    while x > eps:
        x *= 2
        res += str(int(x))
        x -= int(x)

    return res


def bin2float(x):
    return sum(2 ** (-i - 1) for i, digit in enumerate(x) if digit == '1')


def find_code(a, b):
    i = 0
    a += '0' * (len(b) - len(a))
    while a[i] == b[i]:
        i += 1
    res = a[:i] + '0'
    cnt = 0
    while a[i] == 1:
        i += 1
        cnt += 1
    res += '1' * (cnt + 1)
    return res


def coding(word, alphabet, p):
    left, right = 0, 1

    for letter in word:
        i = alphabet.index(letter)
        left, right = (left + (right - left) * sum(p[:i]),
                       left + (right - left) * sum(p[: i + 1]))

    return find_code(*map(float2bin, (left, right)))


def decoding(code, length, alphabet, p):
    code = bin2float(code)
    word = ''
    left, right = 0, 1

    for _ in range(length):
        for i, letter in enumerate(alphabet):
            interval = (left + (right - left) * sum(p[:i]),
                        left + (right - left) * sum(p[:i + 1]))
            if interval[0] <= code < interval[1]:
                word += letter
                code = (code - interval[0]) / (interval[1] - interval[0])
                break

    return word


def main():
    alphabet = 'abcde'
    p = (3/4, 1/16, 1/16, 1/16, 1/16)
    word = 'bed'
    code = coding(word, alphabet, p)
    print(code)
    print(decoding(code, len(word), alphabet, p))

if __name__=='__main__':
    main()
