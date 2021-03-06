import os
import subprocess

files = list(os.walk("src"))
for root, _, files in files:
    for file in files:
        if file.endswith(".hpp"):
            subprocess.run([
                "clang-format",
                "-style=file",
                "-i",
                os.path.join(root,file)
            ])
