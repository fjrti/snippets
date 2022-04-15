
## Text Preprocessing in Python
https://medium.com/@datamonsters/text-preprocessing-in-python-steps-tools-and-examples-bf025f872908

###########################################################
# Concatenate Multiple Text Files
import glob

# Load all txt files in path
files = glob.glob('/path/to/files/*.txt')

# Concatenate files to new file
with open('2020_output.txt', 'w') as out_file:
    for file_name in files:
        with open(file_name) as in_file:
            out_file.write(in_file.read())

# Read file and print
with open('2020_output.txt', 'r') as new_file:
    lines = [line.strip() for line in new_file]
for line in lines: print(line)

###########################################################
# Concatenate Multiple CSV Files Into a DataFrame
import pandas as pd
import glob

# Load all csv files in path
files = glob.glob('/path/to/files/*.csv')

# Create a list of dataframe, one series per CSV
fruit_list = []
for file_name in files:
    df = pd.read_csv(file_name, index_col=None, header=None)
    fruit_list.append(df)

# Create combined frame out of list of individual frames
fruit_frame = pd.concat(fruit_list, axis=0, ignore_index=True)

print(fruit_frame)

###########################################################
# Zip & Unzip Files to Pandas
import pandas as pd

# Create a dataframe to use
df = pd.DataFrame({'col_A': ['kiwi', 'banana', 'apple'],
	           'col_B': ['pineapple', 'grapes', 'grapefruit'],
		   'col_C': ['blueberry', 'grapefruit', 'orange']})

# Compress and save dataframe to file
df.to_csv('sample_dataframe.csv.zip', index=False, compression='zip')
print('Dataframe compressed and saved to file')

# Read compressed zip file into dataframe
df = pd.read_csv('sample_dataframe.csv.zip',)
print(df)

###########################################################
# Flatten Lists
# Create of list of lists (a list where all of its elements are lists)
list_of_lists = [['apple', 'pear', 'banana', 'grapes'], 
                 ['zebra', 'donkey', 'elephant', 'cow'],
	         ['vanilla', 'chocolate'], 
                 ['princess', 'prince']]

# Flatten the list of lists into a single list
flat_list = [element for sub_list in list_of_lists for element in sub_list]

# Print both to compare
print(f'List of lists:\n{list_of_lists}')
print(f'Flattened list:\n{flat_list}')



###########################################################
# Sort List of Tuples
# Some paired data
pairs = [(1, 10.5), (5, 7.), (2, 12.7), (3, 9.2), (7, 11.6)]

# Sort pairs by first entry
sorted_pairs  = sorted(pairs, key=lambda x: x[0])
print(f'Sorted by element 0 (first element):\n{sorted_pairs}')

# Sort pairs by second entry
sorted_pairs  = sorted(pairs, key=lambda x: x[1])
print(f'Sorted by element 1 (second element):\n{sorted_pairs}')

# Extend this to tuples of size n and non-numeric entries
pairs = [('banana', 3), ('apple', 11), ('pear', 1), ('watermelon', 4), ('strawberry', 2), ('kiwi', 12)]
sorted_pairs  = sorted(pairs, key=lambda x: x[0])
print(f'Alphanumeric pairs sorted by element 0 (first element):\n{sorted_pairs}')


###########################################################
# Convert text to lowercase
input_str = ”The 5 biggest countries by population in 2017 are China, India, United States, Indonesia, and Brazil.”
input_str = input_str.lower()
print(input_str)

###########################################################
# Numbers removing
import re
input_str = ’Box A contains 3 red and 5 white balls, while Box B contains 4 red and 2 blue balls.’
result = re.sub(r’\d+’, ‘’, input_str)
print(result)

###########################################################
# Remove punctuation, removes this set of symbols [!”#$%&’()*+,-./:;<=>?@[\]^_`{|}~]:
import string
input_str = “This &is [an] example? {of} string. with.? punctuation!!!!” # Sample string
result = input_str.translate(string.maketrans(“”,””), string.punctuation)
print(result)


###########################################################
# White spaces removal
input_str = “ \t a string example\t “
input_str = input_str.strip()
input_str

###########################################################
# Tokenization
https://docs.google.com/spreadsheets/d/1-9rMhfcmxFv2V2Q5ZWn1FfLDZZYsuwb1eoSp9CiEEOg/edit#gid=1112515333

###########################################################
# Stop words removal
input_str = “NLTK is a leading platform for building Python programs to work with human language data.”
stop_words = set(stopwords.words(‘english’))
from nltk.tokenize import word_tokenize
tokens = word_tokenize(input_str)
result = [i for i in tokens if not i in stop_words]
print(result)

