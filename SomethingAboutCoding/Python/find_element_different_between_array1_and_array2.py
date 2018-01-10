analyst.printColor("red", "IDs exist in both logs:")
print(
	set(unique_IDs_log1) & set(unique_IDs_log2)
	)

analyst.printColor("red", "IDs only in {}:".format(file1))
print(
	set(unique_IDs_log1) - set(unique_IDs_log2)
	)

analyst.printColor("red", "IDs only in {}:".format(file2))
print(
	set(unique_IDs_log2) - set(unique_IDs_log1)
	)