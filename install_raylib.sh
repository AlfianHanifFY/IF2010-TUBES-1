set -e  # Stop kalau ada error

echo "🔧 Installing raylib dependencies..."
sudo apt update
sudo apt install -y build-essential cmake git \
  libgl1-mesa-dev libx11-dev libxcursor-dev libxrandr-dev \
  libxi-dev libxinerama-dev libxxf86vm-dev \
  libopenal-dev libasound2-dev libpulse-dev \
  libvorbis-dev libdrm-dev

echo "📥 Cloning raylib..."
git clone https://github.com/raysan5/raylib.git
cd raylib

echo "🛠️ Building raylib..."
mkdir build && cd build
cmake -DBUILD_SHARED_LIBS=ON ..
make -j$(nproc)

echo "📦 Installing raylib to system..."
sudo make install

echo "✅ raylib installed successfully!"
