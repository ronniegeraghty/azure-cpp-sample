#include <azure/identity.hpp> 
#include <azure/keyvault/secrets.hpp> 
#include <iostream>

using namespace Azure::Security::KeyVault::Secrets;

int main(){
    std::cout<<"Starting Program!"<<std::endl;

    auto const keyVaultUrl = std::getenv("AZURE_KEYVAULT_URL");

    auto credential = std::make_shared<Azure::Identity::DefaultAzureCredential>();

    SecretClient secretClient(keyVaultUrl, credential);
}