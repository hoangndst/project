import React, { useLayoutEffect, useState } from 'react'
import { StyleSheet, Text, View } from 'react-native'
import { Input, Icon, Button } from 'react-native-elements';
import { db } from '../firebase';
const addChat = ( { navigation }) => {

    const [input, setInput] = useState("");

    useLayoutEffect(() => {
        navigation.setOptions({
            title: "Let's Create new Party Due!",
            headerStyle: { backgroundColor: '#2089DC'},
            headerTitleStyle: { color: "#fff", alignSelf: 'auto', fontWeight: "Bold"},
            headerTintColor: 'white',
        });
    }, [navigation]);

    const createChat = async () => {
        await db.collection('chats').add({
            chatName: input
        }).then(() => {
            navigation.goBack();
        }).catch((error) => alert(error));
    }
 
    return (
        <View style={styles.container}>
            <Input
                    style={styles.input}
                    leftIcon={
                        <Icon
                        name='message-square'
                        type='feather'
                        size={20}
                        color='#2D455E'
                        />
                    }
                    type="text"
                    placeholder="Name of Party"
                    value={input}
                    onChangeText={(text) => setInput(text)}
                    onSubmitEditing={createChat}
            />
            <Button 
                title="Create New Party" 
                containerStyle={styles.button}
                onPress={createChat}
            />
            
        </View>
    )
}

export default addChat

const styles = StyleSheet.create({
    container: {
        padding: 30,
    
    },
    button: {
        flex: 1,
    },
    input: {
        height: -10,
        padding: 8,
        marginBottom: 1,
    },
})
