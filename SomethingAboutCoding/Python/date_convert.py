# convert yyyy-mm-dd to date structure
# mark that %Y in capital letter
date_Mazda    = [datetime.datetime.strptime(d, '%Y-%m-%d').date() for d in data_Mazda['“ú•t'][:]]