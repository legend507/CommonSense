def readCSV(filePath):
    import pandas as pd
    data = pd.read_csv(filePath, header=0, encoding='UTF-8')
    return data
def outputAnswer():
    file_answer = './netflix/answer.csv'
    data = readCSV(file_answer)
    print data.shape
    for i in range(data.shape[0]):
        customerID = data['Customer Id'].iloc[i]
        movieID = data[' Movie Id'].iloc[i]
        data.set_value(i, ' Rating', 1.0)           # fastest way to set pandas dataframe
    data.to_csv('./netflix/answer_1.csv', index=False)
    return 
	
	
# find index of a specific value in pandas dataframe
index = data_Mazda.loc[data_Mazda['日付'] == '2015-07-28'].index[0]
# find in range, and reset index
data_stock = data_stock[data_stock['日付'].between(startDate, endDate, inclusive=True)].reset_index()

# iloc[] to get a specific cell
print('Time: {} ~ {}'.format(data1.iloc[0]['時間'], data1.iloc[-1]['時間']))

# convert one colume to hex
data['Data1'] = data['Data1'].apply(lambda x: int(x, base=16))


# iterate row
for index, row in df.iterrows():
    print row['c1'], row['c2']

# iterate column
    for name, values in oneMsg.iteritems():
        print(name)

# check if time in df1 is also in df2
for time in df1['Date]:
    if time not in df2['Date'].values:
        print(time)

