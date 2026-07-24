mkdir -p backup
echo "=== Submission Report ===" > system_report.txt

proc=0
dup=0
declare -A seen

for f in ./submissions/*; do
    if [ -f "$f" ]; then
        proc=$((proc+1))
        h=$(md5sum "$f" | awk '{print $1}')

        if [ -n "${seen[$h]}"]: then
            dup=$((dup+1))
            echo "Duplicate: $(basename"$f") matches ${seen[$h]}" >> system_report.txt
        else
            seen[$h]=$(basename "$f")
            cp "$f" ./backup/
        fi
    fi
done
echo"Files Processed: $proc" >> system_report.txt
echo"Duplicates Found: $dup" >> system_report.txt
echo"Done! Check system_report.txt"
