import pandas as pandas
import matplotlib.pyplot as plt
import os

csv = "experiments/results/results.csv"
if not os.path.exists(csv):
    csv = "results/results.csv"

df = pandas.read_csv(csv)
df['size_mb'] = df['original_size'] / (1024 * 1024)

# Извлекаем чистое имя файла без путей и лишних расширений
df['file_name'] = df['file'].apply(lambda x: x.split('/')[-1].replace('.huff', ''))

df = df.sort_values(by = 'size_mb')

df_encode = df[df['operation'] == 'ENCODE']
df_decode = df[df['operation'] == 'DECODE']

plt.figure(figsize = (12, 7))

# Строим графики
plt.errorbar(x = df_encode['size_mb'], y = df_encode['avg_ms'], yerr = df_encode['sko_ms'], fmt = '-o', capsize = 5, label = 'encode')
plt.errorbar(x = df_decode['size_mb'], y = df_decode['avg_ms'], yerr = df_decode['sko_ms'], fmt = '-o', capsize = 5, label = 'decode')

# ПОДПИСИ ФАЙЛОВ: делаем шахматное расположение для мелких файлов
unique_points = df_encode.drop_duplicates(subset=['size_mb']).reset_index(drop=True)
x_ticks = unique_points['size_mb'].tolist()

x_labels = []
for index, row in unique_points.iterrows():
    # Для четных и нечетных индексов делаем разное количество переносов строк (\n)
    # Это опустит каждую вторую подпись ниже и уберет кашу в начале
    if index % 2 == 0:
        label = f"{row['file_name']}\n({row['size_mb']:.2f} MB)"
    else:
        label = f"\n\n{row['file_name']}\n({row['size_mb']:.2f} MB)"
    x_labels.append(label)

# Применяем новые подписи к оси X
plt.xticks(x_ticks, x_labels, rotation=0, ha='center')

plt.xlabel('Тестируемые файлы и их размер')
plt.ylabel('Время (мс)')
plt.grid(True, linestyle='--', alpha=0.6)
plt.legend()

# Увеличиваем нижний отступ, чтобы шахматная подпись влезла на экран
plt.tight_layout()
plt.show()