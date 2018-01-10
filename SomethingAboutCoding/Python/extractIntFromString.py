# this 2 lines extract number the first from a string
# if string = '45857shit fuck twice'
# then int = 45857

import re
int = int(re.search(r'\d+', string).group())
