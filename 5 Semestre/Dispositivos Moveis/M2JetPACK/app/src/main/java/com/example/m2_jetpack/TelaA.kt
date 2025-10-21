package com.example.m2_jetpack.ui

import androidx.compose.foundation.layout.*
import androidx.compose.material3.*
import androidx.compose.runtime.*
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.unit.dp
import androidx.navigation.NavController

@Composable
fun TelaA(navController: NavController) {
    var texto by remember { mutableStateOf("") }

    Column(
        modifier = Modifier
            .fillMaxSize()
            .padding(16.dp),
        horizontalAlignment = Alignment.CenterHorizontally,
        verticalArrangement = Arrangement.Center
    ) {
        Text("Tela A", style = MaterialTheme.typography.headlineMedium)
        Spacer(Modifier.height(16.dp))
        OutlinedTextField(
            value = texto,
            onValueChange = { texto = it },
            label = { Text("Digite seu nome") }
        )
        Spacer(Modifier.height(16.dp))
        Button(onClick = {
            if (texto.isNotEmpty()) {
                navController.navigate("telaB/$texto")
            }
        }) {
            Text("Ir para Tela B")
        }
    }
}
