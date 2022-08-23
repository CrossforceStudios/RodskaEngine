@echo off 

echo "Setting up Mono..."
pushd ..\..\
    git clone https://github.com/mono/mono RodskaEngine/vendor/mono
popd
echo "Done."
pause
