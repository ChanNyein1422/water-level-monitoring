const express = require("express");
const fs = require("fs");
const app = express();
const port = 3000;
const cors = require("cors");
app.use(cors());

// Middleware to parse JSON data
app.use(express.json());

// Route to receive data from ESP32
app.post("/save_data", (req, res) => {
  const { timestamp, distance } = req.body;
  if (!timestamp || !distance) {
    return res.status(400).send("Missing data");
  }
  const data = `${timestamp},${distance}\n`;
  fs.stat("water_level.csv", (err, stats) => {
    if (err) {
      if (err.code === "ENOENT") {
        fs.writeFile(
          "water_level.csv",
          "Timestamp,Distance\n" + data,
          (err) => {
            if (err) {
              console.error("Error writing file:", err);
              return res.status(500).send("Error saving data");
            }
            res.status(200).send("Data saved successfully");
          }
        );
      }
    } else {
      fs.appendFile("water_level.csv", data, (err) => {
        if (err) {
          console.error("Error saving data:", err);
          return res.status(500).send("Error saving data");
        }
        res.status(200).send("Data saved successfully");
      });
    }
  });
});

app.listen(port, () => {
  console.log(`Server running at http://localhost:${port}`);
});
