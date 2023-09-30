import os

def count_files(folder_path):
    count = 0
    for _, _, files in os.walk(folder_path):
        count += len(files)
    return count

def count_files_in_vault(vault_folder):
    total_count = 0
    skip = ["Draft", "Library"]
    table = ""
    for dir in os.listdir(vault_folder):
        if dir in skip:
            continue
        folder_path = os.path.join(vault_folder, dir)
        if os.path.isdir(folder_path):
            file_count = count_files(folder_path)
            total_count += file_count
            table += f"{dir} : {file_count} \n"

    total = f"Total number of problems: {total_count}"
    table += total
    return table

vault_folder = "/Users/mabook/Documents/AlgorithmPractice/Vault/"  
table = count_files_in_vault(vault_folder)

print(table)

# Read the existing contents of the README file
with open("README.md", "r") as file:
    lines = file.readlines()

# Find the line number where "===STAT===" is located
stat_line_number = None
for i, line in enumerate(lines):
    if line.strip() == "## STAT":
        stat_line_number = i
        break

if stat_line_number is not None:
    lines = lines[:stat_line_number + 1] + ["\n", table]


# Write the modified contents back to the README file
with open("README.md", "w") as file:
    file.writelines(lines)
