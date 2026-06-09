import pandas as pandas
import matplotlib.pyplot as plt
import seaborn as sns
import os

csv = "experiments/results/results.csv"
if not os.path.exists(csv):
    csv = "results/results.csv"

df = pandas.read_csv(csv)
df['size_mb'] = df['original_size'] / (1024 * 1024)

df['file'] = df['file'].apply(lambda x: x.split('/')[-1])

df = df.sort_values(by = 'size_mb')

df_decode = df[df['operation'] == 'DECODE']
df_encode = df[df['operation'] == 'ENCODE']

plt.figure(figsize = (10,6))

plt.errorbar(x = df_encode['size_mb'], y = df_encode['encode_avg_ms'], yerr = df_encode['encode_sko_ms'], fmt = '-o', capsize = 5, label = 'encode')
plt.errorbar(x = df_decode['size_mb'], y = df_decode['encode_avg_ms'], yerr = df_decode['encode_sko_ms'], fmt = '-o', capsize = 5, label = 'decode')

plt.xlabel('Размер файла (Мегабайт)')
plt.ylabel('Время (мс)')
plt.grid(True)
plt.legend()
plt.show()


