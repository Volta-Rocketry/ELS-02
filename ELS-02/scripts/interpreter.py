import pandas as pd
import os

INPUT_FILE = "flight_log.csv" 
OUTPUT_FILE = "processed_telemetry.xlsx"

COLUMNS = [
    "Global_time_ms",
    "Accel_X", "Accel_Y", "Accel_Z",
    "Lin_vel_X", "Lin_vel_Y", "Lin_vel_Z",
    "Ang_vel_X", "Ang_vel_Y", "Ang_vel_Z",
    "Mag_X", "Mag_Y", "Mag_Z",
    "Bulk_Def_1", "Bulk_Def_2", "Bulk_Def_3",
    "Air_Def_1", "Air_Def_2", "Air_Def_3", "Air_Def_4",
    "Air_Load_1", "Air_Load_2", "Air_Load_3", "Air_Load_4",
    "Pressure_Pa", "Altitude_Baro",
    "Temp_1", "Temp_2", "Temp_3", "Temp_4",
    "Audio_PCM",
    "Filt_Accel_X", "Filt_Accel_Y", "Filt_Accel_Z",
    "Filt_Gyro_X", "Filt_Gyro_Y", "Filt_Gyro_Z",
    "Filt_Alt",
    "Est_Pos_X", "Est_Pos_Y", "Est_Pos_Z",
    "Est_Sigma_X", "Est_Sigma_Y", "Est_Sigma_Z"
]

def process_log():
    if not os.path.exists(INPUT_FILE):
        print(f"[ERROR] It cannot be found {INPUT_FILE}")
        return

    try:
        df = pd.read_csv(INPUT_FILE, header=None)
        
        # Columns check
        columns_csv = df.shape[1]
        columns_expected = len(COLUMNS)
        
        print(f"Columns detected: {columns_csv}")
        print(f"Columns expected: {columns_expected}")

        if columns_csv != columns_expected:
             print("[WARNING] Column difference. Check 'telemetry_structures.h' vs Python.")
        else:
             print("[OK] Correct structrure.")

        df.columns = COLUMNS[:columns_csv]

        df.to_excel(OUTPUT_FILE, index=False)
        print(f"[SUCCESS] Processed data stored in {OUTPUT_FILE}")

    except Exception as e:
        print(f"[ERROR] The processing failed: {e}")

if __name__ == "__main__":
    process_log()
