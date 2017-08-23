import re

f = open('testCode.txt', 'r+')
m = re.sub(r'(?<!")([0-9]+)(?!")', r'"\1"' , f.read())
f.seek(0)
f.truncate()

f.write(m)

print(m)

f.close()
