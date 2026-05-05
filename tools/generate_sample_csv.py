import argparse
import csv
import random
from pathlib import Path


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--rows", type=int, default=100000)
    parser.add_argument("--broken", type=int, default=50)
    parser.add_argument("--out", type=str, default="samples/sample_broken.csv")
    args = parser.parse_args()

    out_path = Path(args.out)
    out_path.parent.mkdir(parents=True, exist_ok=True)

    broken_rows = set(random.sample(range(2, args.rows + 1), min(args.broken, args.rows - 1)))

    headers = ["id", "name", "category", "value", "memo"]

    with out_path.open("w", newline="", encoding="utf-8") as f:
        writer = csv.writer(f)
        writer.writerow(headers)

        for i in range(1, args.rows + 1):
            if i in broken_rows:
                if i % 2 == 0:
                    writer.writerow([i, f"name_{i}", "A"])
                else:
                    writer.writerow([i, f"name_{i}", "B", random.randint(1, 1000), "memo", "extra_column"])
            else:
                memo = f'this is memo, with comma {i}' if i % 10 == 0 else f"memo_{i}"
                writer.writerow([i, f"name_{i}", random.choice(["A", "B", "C"]), random.randint(1, 1000), memo])

    print(f"[OK] generated: {out_path}")
    print(f"rows={args.rows}, broken={len(broken_rows)}")


if __name__ == "__main__":
    main()